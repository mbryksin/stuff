open System
open System.Net
open System.Xml
open Microsoft.FSharp.Control.WebExtensions
open System.Drawing
open System.Windows.Forms
open HtmlAgilityPack
open System.Collections.Concurrent
open FSharp.Control

let form = new Form(Visible=true, Text="NetworkGUI")
let container = new TableLayoutPanel(ColumnCount=2, RowCount=2)
let label = new Label(Text="Address:")
let address = new TextBox()
let content = new WebBrowser()
let webClient = new WebClient()
let links = new ConcurrentDictionary<string, bool>()
let downloaded = new ConcurrentDictionary<string, bool>()

label.TextAlign <- ContentAlignment.MiddleRight
address.Text <- "http://se.math.spbu.ru/SE"
form.Width <- 800
form.Height <- 600
container.Dock <- DockStyle.Fill
address.Dock <- DockStyle.Fill
content.Dock <- DockStyle.Fill
form.Controls.Add(container)
container.Controls.Add(label, 0, 0)
container.Controls.Add(address, 1, 0)
container.Controls.Add(content, 0, 1)
container.SetColumnSpan(content, 2)
content.Refresh()

let downloadImg(url:string) =
    if not(downloaded.ContainsKey(url))
      then
        downloaded.GetOrAdd(url, true) |> ignore
        try
            let x = url.Length
            webClient.DownloadFileAsync(Uri(url),url)
            printfn "download: %s" url
        with
            | ex -> printfn "%s" (ex.Message);

let extractLinks (doc:HtmlDocument) = 
    try
        [ for nd in doc.DocumentNode.SelectNodes("//a[@href]") do
            if nd.Attributes.["href"].Value.StartsWith("http://") then yield nd.Attributes.["href"].Value ]
    with _ -> []

let extractPics (doc:HtmlDocument) = 
    try
        [ for nd in doc.DocumentNode.SelectNodes("//img") do
            let src = nd.Attributes.["src"].Value
            if src.EndsWith(".jpg") || src.EndsWith(".png") || src.EndsWith(".gif") then yield src ]
    with _ -> []

let downloadDocument (url:string) = 
    async {
    try
        let! html = webClient.AsyncDownloadString(Uri(url))
        let doc = new HtmlDocument()
        doc.LoadHtml(html)
        return Some doc
    with
        | _ -> return None
    }

let rec fetchAsync(url:string) = asyncSeq {
    if not(links.ContainsKey(url)) 
      then
        links.GetOrAdd(url, true) |> ignore 
        let! doc = downloadDocument url
        match doc with
        | Some doc ->
            for pic in extractPics doc do 
                printfn "pic: %s" pic
                downloadImg pic 
            for link in extractLinks doc do
                printfn "link: %s" link
                yield! fetchAsync link 
        | _ -> ()
}

address.KeyDown.Add(
 fun e -> if e.KeyCode = Keys.Enter then
    try 
        content.Url <- System.Uri(address.Text)
        fetchAsync address.Text
            |> AsyncSeq.take 10
            |> AsyncSeq.iter (printfn "%s")
            |> Async.Start
    with _ -> ()
 )

form.Show()
#if COMPILED
[<STAThread()>]
Application.Run(form)
#endif