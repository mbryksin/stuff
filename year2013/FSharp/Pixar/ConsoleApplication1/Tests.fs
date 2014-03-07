module Tests

open Main
open FsUnit
open NUnit.Framework
open NSubstitute

type MockFactory(d,l,w,m) =
    interface IWeatherFactory with
        member this.CreateDayLight() = {new IDaylight with member x.Current = d}
        member this.CreateLuminary() = {new ILuminary with member x.IsShining() = l}
        member this.CreateWind() = {new IWind with member x.Speed = w}
        member this.CreateMagic() = m
(*
[<TestFixture>] 
type ``Weather testing``()=
    let cloud = new Cloud(new WeatherFactory(Morning, true, 0))

    [<Test>] member x.
     ``test1`` ()=
        cloud.Create().CreatureType |> should equal Puppy
        *)

[<TestFixture>] 
type ``DinamicMock``() = 
    [<Test>] member x.
     ``Test GiveBaby called Once`` ()= 
        let m = Substitute.For<IMagic>()
        let courier = Substitute.For<ICourier>()
        m.CallCourier(Arg.Any<CreatureType>()).Returns(courier) |> ignor

        let wf = new WeatherFactory(Night, true, 1, m)
        let cloud = new Clound(wf)
        cloud.Create |> ignore  //().CreatureType |> should equal CreatureType.Bat

        courier.Received(1).GiveBaby(Arg.Any<Creature>())
        //запустить тесты 0, 1, 2


    
        