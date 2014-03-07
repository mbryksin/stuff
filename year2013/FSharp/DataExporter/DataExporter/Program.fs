(*
 Data Exporter
*)

open System

[<AbstractClass>]
type DataExporter() =
    let mutable data = ""
    member this.Data with get() = data and set(str:string) = data <- str

    member this.ReadData() = this.Data <- "This is a example of Template Method design pattern1"
    abstract member FormatData:unit -> unit
    default this.FormatData() = this.Data <- this.Data.ToUpper()
    abstract member ExportData:unit -> unit
    member this.ExportFormatedData() =
        this.ReadData()
        this.FormatData()
        this.ExportData()

type ExcelExporter() = 
    inherit DataExporter()
    override this.ExportData() = printfn "Export to Excel [%s]" <| this.Data
 
type PDFExporter() = 
    inherit DataExporter()
    override this.FormatData() = this.Data <- this.Data.ToLower()
    override this.ExportData() = printfn "Export to PDF [%s]" <| this.Data
    
[<EntryPoint>]
let main argv = 
    let excelexporter = new ExcelExporter()// :> DataExporter
    excelexporter.ExportFormatedData()
    let pdfexporter = new PDFExporter()// :> DataExporter
    pdfexporter.ExportFormatedData()
    0 // return an integer exit code
