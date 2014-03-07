module SnakeObj

open System

let random = new Random()
type Directions = Left | Right | Up | Down

type Snake(size:int) =
    class
    let mutable score = 0
    let mutable direction = Down
    let mutable gameOver = false
    let mutable points = [(0,2); (0,1); (0,0)]
    let mutable food = (size / 2, size / 2)
    let gameOverEvent = new Event<_>()

    member this.Direction 
        with get() = direction 
        and set(x:Directions) = 
            if (x = Left) && (direction = Right) || (x = Right) && (direction = Left) ||
               (x = Up) && (direction = Down) || (x = Down) && (direction = Up)
                then ignore()
                else direction <- x
    member this.Points = points
    member this.Food = food
    member this.Score = score
    member this.GameOverEvent = gameOverEvent.Publish

    member this.Move() =
        this.Add()
        if this.Head() = food
            then 
                score <- score + 100
                food <- (random.Next(0, size), random.Next(0, size))
                while (List.length (points |> List.filter (fun x -> x = food)) > 0) do
                    food <- (random.Next(0, size), random.Next(0, size))
            else this.Remove()
        this.CheckGameOver()
        if gameOver then gameOverEvent.Trigger()
   
    member this.Head() = 
        match points with
        | head :: tail -> head
        | _            -> failwith "data error"

    member this.Add() =
        match direction with
        | Up ->
            points <- (fst <| this.Head(), (snd <| this.Head()) - 1) :: points
        | Down ->
            points <- (fst <| this.Head(), (snd <| this.Head()) + 1) :: points
        | Right ->
            points <- ((fst <| this.Head()) + 1, snd <| this.Head()) :: points
        | Left ->
            points <- ((fst <| this.Head()) - 1, snd <| this.Head()) :: points

    member private this.Remove() = 
        let rec removelast list =
            match list with
            | head :: []   -> []
            | head :: tail -> head :: removelast tail
            | _            -> failwith "list pattern matching failed"
        points <- removelast points
    
    member this.CheckGameOver() =
        match points |> List.filter (fun x -> (fst x < 0) || (fst x >= size) || (snd x < 0) || (snd x >= size)) with
        | head :: tail -> gameOver <- true
        | _            -> ignore()
        
        points |> List.iter (fun x -> if List.length (
                                                     points |> List.filter (fun y -> x = y) 
                                                     ) >= 2
                                          then gameOver <- true
                            )

    end