module CustomForm

open SnakeObj

open System.Windows.Forms
open System.ComponentModel
open System.Drawing

type AppForm(size:int) as this =
    class
    inherit Form()
    let snake = new Snake(size)
    let timer = new Timer()
    let pb = new PictureBox()
    let pinkBrush = new SolidBrush(Color.Pink)
    let blueBrush = new SolidBrush(Color.Blue)
    let aquaBrush = new SolidBrush(Color.Aqua)    
    let mutable blockSize = 20

    let TimerEventProcessor(evArgs) =
        snake.Move()
        pb.Refresh()
        
    do  
        this.Width   <- size * blockSize + 16
        this.Height  <- size * blockSize + 39
        pb.Width     <- size * blockSize
        pb.Height    <- size * blockSize
        timer.Interval <- 1000
        snake.GameOverEvent.Add(fun () -> this.StopGame())
        timer.Tick.Add(TimerEventProcessor)
        this.KeyDown |> Event.add (fun evArgs -> 
                                        match evArgs.KeyCode with
                                        | Keys.Enter  -> this.StartGame()
                                        | Keys.Escape -> this.StopGame()
                                        | _           -> ignore() 
                                  )
        
        pb.Dock <- DockStyle.Fill
        pb.BackColor <- Color.White
        pb.Paint |> Event.add(this.pb_Paint)
        
        this.Controls.Add(pb);
    
    member private this.DrawRect(e:PaintEventArgs, brush, X, Y) =
        e.Graphics.FillRectangle(brush, new Rectangle(X * blockSize , Y * blockSize, blockSize, blockSize))

    member this.pb_Paint(e:PaintEventArgs) =
        this.DrawRect(e, pinkBrush, fst snake.Food, snd snake.Food)
        snake.Points |> List.iter (fun x -> this.DrawRect(e, aquaBrush, fst x, snd x))
        this.DrawRect(e, blueBrush, fst <| snake.Head(), snd <| snake.Head())

    member this.StartGame() =
        this.KeyDown |> Event.add (fun evArgs -> 
                                        match evArgs.KeyCode with
                                        | Keys.Down   -> snake.Direction <- Down
                                        | Keys.Up     -> snake.Direction <- Up
                                        | Keys.Left   -> snake.Direction <- Left
                                        | Keys.Right  -> snake.Direction <- Right
                                        | _           -> ignore() 
                                  )        
        timer.Start()
    
    member this.StopGame() =
        timer.Stop()
        this.Close()
        printfn "Game over =("
        printfn "Your score %A" snake.Score
        
    end

printfn "HELP: Press Esc to quit"
printfn "Press Enter to start..."
let appForm = new AppForm(10)
appForm.FormBorderStyle <- FormBorderStyle.FixedDialog
Application.Run(appForm)

