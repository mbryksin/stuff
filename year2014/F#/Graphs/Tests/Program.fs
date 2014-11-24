open GraphLibrary
open QuickGraph
open NUnit.Framework
open FsUnit

[<TestFixture>]
type TestClass() = 

    static member testRobson(v, e, num) =
        let result = Algorithm.Robson(v, e)
        Seq.length result = num

    [<Test>] member test.
     ``1 вершина`` ()=
        TestClass.testRobson([0],[],1) |> should be True
    
    [<Test>] member test.
     ``2 вершины, 1 ребро`` ()=
        TestClass.testRobson([0;1],[new Edge<int>(0,1)],1) |> should be True
    
    [<Test>] member test.
     ``3 вершины, 2 ребра`` ()=
        TestClass.testRobson([0;1;2],[new Edge<int>(0,1);new Edge<int>(2,1)],2) |> should be True

    [<Test>] member test.
     ``5 вершин, 4 ребра`` ()=
        TestClass.testRobson([0;1;2;3;4],[new Edge<int>(0,1);new Edge<int>(2,1);new Edge<int>(2,3);new Edge<int>(3,4)],3) |> should be True
