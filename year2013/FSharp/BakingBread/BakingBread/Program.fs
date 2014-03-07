(*
BAKING BREAD
*)

open System;
open System.Collections;

[<AbstractClass>]
type Bread() = 
    abstract member Type:string

type Baton() =
    inherit Bread()
    override this.Type = "Батон"

type Baget() =
    inherit Bread()
    override this.Type = "Багет"

type BlackBread() =
    inherit Bread()
    override this.Type = "Бородинский хлеб"
    
type Plushka() =
    inherit Bread()
    override this.Type = "Плюшка"

[<AbstractClass>] 
type Creator() = 
    abstract member FactoryMethod: Bread

type CreatorBaton() =
    inherit Creator()
    override this.FactoryMethod = new Baton() :> Bread

type CreatorBaget() =
    inherit Creator()
    override this.FactoryMethod = new Baget() :> Bread

type CreatorBlackBread() =
    inherit Creator()
    override this.FactoryMethod = new BlackBread() :> Bread

type CreatorPlushka() =
    inherit Creator()
    override this.FactoryMethod = new Plushka() :> Bread

[<EntryPoint>]
let main argv = 
    let creators = [new CreatorBaton() :> Creator; 
                    new CreatorBaget() :> Creator;
                    new CreatorBlackBread() :> Creator;
                    new CreatorPlushka() :> Creator]

    List.iter (fun (x:Creator) -> printfn "%s" <| x.FactoryMethod.Type) creators
    0 // return an integer exit code

(*
[<AbstractClass>] 
type Creator() = 
    abstract member FactoryMethod:string -> Bread

type CreatorBread() =
    inherit Creator()
    override this.FactoryMethod(t:string) =
        match t with
        | "Батон" -> new Baton() :> Bread
        | "Багет" -> new Baget() :> Bread
        | "Бородинский хлеб" -> new BlackBread() :> Bread
        | "Плюшка" -> new Plushka() :> Bread
        | _ -> failwith "Булки кончились"

[<EntryPoint>]
let main argv = 
    let creator = new CreatorBread()
    let breadlist = ["Батон"; "Багет"; "Бородинский хлеб"; "Плюшка"]

    List.iter (fun x -> printfn "%s" <| creator.FactoryMethod(x).Type) breadlist
    0 // return an integer exit code
*)