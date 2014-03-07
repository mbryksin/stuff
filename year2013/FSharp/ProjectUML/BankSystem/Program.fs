(*
Copyright 2013 Matvey Bryksin

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*)

open System

[<AbstractClass>]
type Service(name:string, cost:int, time:int) =
    let mutable title = name
    let mutable deadline = time
    let mutable price = cost
    abstract member update: unit -> unit
    member this.serviceTitle = title
    member this.cost = price
    member this.timeLeft = deadline
    member this.rebranding(name:string) = title <- name
    member this.changeCost(cost:int) = price <- cost
    member this.timeOut = deadline <- deadline - 1

type Client(name: string, startmoney: int) =
    let mutable budget = startmoney
    let mutable (services: List<Service>) = []
    override this.ToString() = 
        let mutable x = String.Concat(name, " budget: ", budget.ToString())
        match services with
        | [] -> x <- String.Concat(x," no services connected")
        | _ -> x <- String.Concat(x, " services: ", List.foldBack (fun (s:Service) acc -> String.Concat(s.serviceTitle,", ",acc)) services "")
        x
    member this.clientName with get() = name
    member this.money with get() = budget
    member this.addMoney(money:int) = budget <- budget + money
    member this.doService() =
        List.map (fun (x:Service) -> if x.timeLeft <> 0 then budget <- budget - x.cost; x.update()) services |> ignore
    member this.connectService(service:Service) = services <- List.append [service] services

type LegalEntity(company: string, startmoney: int, contactname: string) =
    inherit Client(company, startmoney)
    let mutable financialHistory = []
    let mutable contactname = contactname    
    member this.contactName with get() = contactname and set(name:string) = contactname <- name
    member this.printFinanceHistory =
        printfn "%s finance history:" company
        List.iter (fun x -> printfn "* %A" x) financialHistory
    member this.addToFinanceHistory(finances:List<int>) =
        financialHistory <- List.append finances financialHistory
    member this.addToFinanceHistory(finance:int) = financialHistory <- List.append [finance] financialHistory

type Individual(name: string, startmoney:int, everymonthincome: int) = 
    inherit Client(name, startmoney)
    let mutable income = everymonthincome
    member this.salary with get() = income and set value = income <- value
    member this.getSalary() = this.addMoney(income)

type Deposit(name: string, size:int, percent:int, time:int) = 
    inherit Service(name, -size*percent/100, time)
    let mutable contribution = size
    override this.ToString() = "Deposite: size " + contribution.ToString() + " persent " + percent.ToString() + "% time left " + this.timeLeft.ToString()  + " month"
    override this.update() =  
        this.timeOut
        contribution <- contribution + contribution*percent/100
        this.changeCost(-contribution*percent/100)

type Credit(typecredit:string, size:int, percent:int, time:int) =
    inherit Service(typecredit, size*percent/100, time)
    let mutable credit = size
    override this.ToString() = this.purpose + ": size " + credit.ToString() + " persent " + percent.ToString() + "% time left " + this.timeLeft.ToString() + " month"
    abstract purpose : string with get
    default this.purpose with get() = "money credit"
    override this.update() =
        this.timeOut
        credit <- credit - credit*percent/100
        this.changeCost(credit*percent/100)
      
type Mortgage(address:string, size:int, persent:int, time:int) =
    inherit Credit("mortgage", size, persent, time)
    override this.purpose with get() = "mortgage " + address

type ConsumerCredit(subject:string, size:int, persent:int, time:int) =
    inherit Credit("customer credit", size, persent, time)
    override this.purpose with get() = "credit for " + subject

printfn "-------------------"
printfn "persons:"

let person1 = new Individual("Joe Johnson", 10000, 1000)
let person2 = new Individual("John Smith", 20000, 2000)
person1.getSalary()
printfn "%s" <| person1.ToString()
printfn "%s" <| person2.ToString()

printfn "-------------------"
printfn "company:"

let company1 = new LegalEntity("Tests Inc.", 1000000, "Joe Jack")
printfn "%s" <| company1.ToString()
company1.addToFinanceHistory(1000000)
company1.addToFinanceHistory([1100000; 1200000; 2000000])
company1.printFinanceHistory

printfn "-------------------"
printfn "services:"

let deposit1 = new Deposit("Deposit1", 10000, 5, 10)
let deposit2 = new Deposit("Deposit2", 12000, 4, 12)
let deposit3 = new Deposit("Deposit3", 15000, 2, 15)
let credit1 = new ConsumerCredit("car", 1000, 10, 10)
let credit2 = new Credit("Credit", 100000, 20, 2)
let credit3 = new Mortgage("Leninskyi prospect 114/72", 500000, 1, 1000)

printfn "%s" <| credit1.ToString()
printfn "%s" <| credit2.ToString()
printfn "%s" <| credit3.ToString()
printfn "%s" <| deposit1.ToString()
printfn "%s" <| deposit2.ToString()
printfn "%s" <| deposit3.ToString()

person1.connectService(deposit1)
person1.connectService(deposit2)
person1.connectService(credit3)
person2.connectService(deposit3)
person2.connectService(credit1)
company1.connectService(credit2)

printfn "-------------------"
printfn "clients:"

printfn "%s" <| person1.ToString()
printfn "%s" <| person2.ToString()
printfn "%s" <| company1.ToString()

printfn "-------------------"
printfn "company starts to pay credit:"
company1.doService()
printfn "%s money: %s" <| company1.clientName <| company1.money.ToString()
printfn "%s" <| credit2.ToString()
company1.doService()
printfn "%s money: %s" <| company1.clientName <| company1.money.ToString()
printfn "%s" <| credit2.ToString()
company1.doService()
printfn "%s money: %s" <| company1.clientName <| company1.money.ToString()
printfn "%s" <| credit2.ToString()

printfn "-------------------"
printfn "persons do service's responsibilities:"

person1.doService()
person2.doService()
printfn "%s" <| deposit1.ToString()
printfn "%s" <| deposit2.ToString()
printfn "%s" <| deposit3.ToString()
printfn "%s" <| credit1.ToString()
printfn "%s" <| credit3.ToString()
printfn "%s money: %s" <| person1.clientName <| person1.money.ToString()
printfn "%s money: %s" <| person2.clientName <| person2.money.ToString()