module Main

open System

type CreatureType = Puppy   | Kitten | Hedgedog | Bearcub | Piglet | Bat | Balloon
type DaylightType = Morning | Noon   | Evening  | Night
type CourierType  = Stork   | Daemon

type Creature(t: CreatureType) =
    member this.CreatureType = t

type IWind = 
    abstract member Speed:int
type IDaylight =
    abstract member Current:DaylightType
type ILuminary =
    abstract member IsShining:unit -> bool
type ICourier =
    abstract member GiveBaby: Creature -> unit
type IMagic =
    abstract member CallCourier:CreatureType -> ICourier

type Stork() = 
    interface ICourier with
        member x.GiveBaby(_) = ()

type IWeatherFactory = 
    abstract member CreateDayLight: unit -> IDaylight
    abstract member CreateLuminary:unit -> ILuminary
    abstract member CreateWind: unit -> IWind
    abstract member CreateMagic: unit -> IMagic


type Cloud(factory:IWeatherFactory) =
    let daylight = factory.CreateDayLight()
    let luminary = factory.CreateLuminary()
    let wind = factory.CreateWind()
 
    member x.InternalCreate() =
      if daylight.Current = DaylightType.Night then
        if luminary.IsShining() then
          new Creature(CreatureType.Bat)
      // TODO – implement all other creatures
      //elif
        else
          raise <| new System.NotImplementedException()
      else
        raise <| new System.NotImplementedException()
 
    member x.Create() =
      let creature = x.InternalCreate()
      let magic = factory.CreateMagic()
      magic.CallCourier(creature.CreatureType).GiveBaby(creature)
      creature

(*
type Wind() =
    let rnd = new Random()
    interface IWind with member this.Speed = rnd.Next(11)

type Daylight() =   
    let rnd = new Random() 
    interface IDaylight with 
        member this.Current =
            let value = rnd.Next(4) 
            match value with
            | 0 -> DaylightType.Morning
            | 1 -> DaylightType.Noon
            | 2 -> DaylightType.Evening
            | 3 -> DaylightType.Night
            | _ -> DaylightType.Night

type Luminary() =
    let rnd = new Random() 
    interface ILuminary with 
        member this.IsShining() = rnd.Next(2) = 1
*)