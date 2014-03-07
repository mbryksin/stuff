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
open System.Text.RegularExpressions
open NUnit.Framework
open FsUnit
open FsUnit.Xunit
open Xunit

//username@hostname
let hostname = "([a-z0-9]([-a-z0-9]{0,61}[a-z0-9])?\.)*(aero|arpa|asia|biz|cat|com|coop|edu|gov|info|int|jobs|mil|mobi|museum|name|net|org|pro|tel|travel|[a-z][a-z])$"
let username = "^[-a-zA-Z0-9!#$%&'*+/=?^_`{|}~]+(\.[-a-zA-Z0-9!#$%&'*+/=?^_`{|}~]+)*"
let email = username + "@" + hostname

[<TestFixture>] 
type ``emails checking``()=
    let regexp = new Regex(email)

    [<Test>] member x.
     ``my email``()=
        regexp.IsMatch("matvey.bryksin@gmail.com") |> should be True

    [<Test>] member x.
     ``Victor Polozov's email``()=
        regexp.IsMatch("victorp@math.spbu.ru") |> should be True

    [<Test>] member x.
     ``mister example email``()=
        regexp.IsMatch("mr.example111@mail.ru") |> should be True

    [<Test>] member x.
     ``up or down case crazy email``()=
        regexp.IsMatch("ANGER.sch00lboY!!1111!!.DArk_NIght777@2hardcore.net") |> should be True

    [<Test>] member x.
     ``strange symbols email``()=
        regexp.IsMatch("a#$.%.&^_`{!-|-!}l__l.``\'o\'+.+h~A=@cm.ru") |> should be True

    [<Test>] member x.
     ``no at email``()=
        regexp.IsMatch("angry.bird.com") |> should be False
    
    [<Test>] member x.
     ``no at no domain email``()=
        regexp.IsMatch("angry.bird") |> should be False
    
    [<Test>] member x.
     ``no domain email``()=
        regexp.IsMatch("angry@beardyman") |> should be False

    [<Test>] member x.
     ``two at email``()=
        regexp.IsMatch("angry@beardyman@ya.ru") |> should be False

    [<Test>] member x.
     ``quote email``()=
        regexp.IsMatch("this\"email\is\not\\avaliable@ya.ru") |> should be False
