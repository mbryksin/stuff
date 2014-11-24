namespace GraphLibrary
open QuickGraph

type Algorithm private () = 
    
    static member createGraph(vertices, edges) =
        let graph = new UndirectedGraph<int, Edge<int>>()
        Seq.iter (fun e -> graph.AddVerticesAndEdge(e) |> ignore) edges
        Seq.iter (fun v -> graph.AddVertex(v) |> ignore) vertices
        graph

    static member neighbors(v, (graph:UndirectedGraph<int, Edge<int>>)) = 
        graph.AdjacentEdges(v) |> Seq.fold (fun acc e -> Seq.append [e.Target] acc) Seq.empty

    static member dominates(A: int, B: int, graph: UndirectedGraph<int, Edge<int>>) =
        let Na = (Algorithm.neighbors(A,graph)) |> Seq.append [A]
        let Nb = (Algorithm.neighbors(B,graph)) |> Seq.append [B]
        if (Seq.length Na) > (Seq.length Nb)
            then
                Seq.fold (fun acc x -> (Seq.exists ((=)x) Na) && acc) true Nb    
            else false
    
    static member sortpairs(graph: UndirectedGraph<int, Edge<int>>, vertexset: seq<int>):seq<int*int> =
        let rec qsort(xs:list<int*int>) =
            let smaller = xs |> List.filter(fun (_,e) -> e < snd(Seq.head xs) )
            let larger = xs |> List.filter(fun (_,e) -> e > snd(Seq.head xs) )
            match xs with
            | [] -> []
            | _ -> qsort(smaller)@[xs.Head]@qsort(larger)

        let pair_degrees = Seq.map (fun v -> (v,graph.AdjacentDegree(v)) ) vertexset
        let result = (Seq.toList pair_degrees) |> qsort :> seq<int*int>
        result

    static member ms2(graph: UndirectedGraph<int, Edge<int>>, vertexset: seq<int>):seq<int> = 
        let edges2(vj,vk) = 
            let g5 = Algorithm.createGraph(graph.Vertices, graph.Edges)
            g5.RemoveVertex(fst vj) |> ignore
            g5.RemoveVertex(fst vk) |> ignore
            Seq.iter (fun v -> g5.RemoveVertex(v)|>ignore) (Algorithm.neighbors(fst vj,graph))
            Seq.iter (fun v -> g5.RemoveVertex(v)|>ignore) (Algorithm.neighbors(fst vk,graph))
            Algorithm.ms(g5) |> Seq.append [(fst vj);(fst vk)]
        let edge1(vi,vj,vk) = 
            let g5 = Algorithm.createGraph(graph.Vertices, graph.Edges)
            g5.RemoveVertex(fst vk) |> ignore
            Seq.iter (fun v -> g5.RemoveVertex(v) |> ignore) (Algorithm.neighbors(fst vk,graph))
            Algorithm.ms1(g5,[vi;vj]) |> Seq.append [(fst vk)]
        let vertexN(si,sj) =
            let nSi = Algorithm.neighbors(si,graph)
            let nSj = Algorithm.neighbors(sj,graph)
            let nSi_Sj = Seq.fold (fun acc x -> if (Seq.exists ((=)x) nSj) then (Seq.append acc [x]) else acc) Seq.empty nSi
            let NSiSj = Seq.toList nSi_Sj
            match NSiSj with
            | x::xs -> Some x
            | [] -> None
        let returnIS(v, set) = 
            let g5 = Algorithm.createGraph(graph.Vertices, graph.Edges)
            g5.RemoveVertex(v) |> ignore
            Algorithm.ms2(g5, set)

        let pair_sorted = Algorithm.sortpairs(graph,vertexset)
        let lenght = Seq.length pair_sorted
        match (lenght) with
        | 0 -> Seq.empty
        | 1 -> Seq.empty
        | 2 -> let take2 = Seq.take 2 pair_sorted
               let s1 = Seq.head take2
               let s2 = Seq.last take2

               let g3 = Algorithm.createGraph(graph.Vertices, graph.Edges)
               g3.RemoveVertex(fst s1) |> ignore
               g3.RemoveVertex(fst s2) |> ignore
               Seq.iter (fun v -> g3.RemoveVertex(v)|>ignore) (Algorithm.neighbors(fst s1,graph))
               Seq.iter (fun v -> g3.RemoveVertex(v)|>ignore) (Algorithm.neighbors(fst s2,graph))
        
               if graph.ContainsEdge(fst s1,fst s2)
                   then Seq.empty
                   else Algorithm.ms(g3) |> Seq.append [(fst s1);(fst s2)]

        | 3 -> let take2 = Seq.take 2 pair_sorted
               let s1 = Seq.head take2
               let s2 = Seq.last take2
               let s3 = Seq.last pair_sorted
               
               let g1 = Algorithm.createGraph(graph.Vertices, graph.Edges)
               g1.RemoveVertex(fst s1) |> ignore
               Seq.iter (fun v -> g1.RemoveVertex(v) |> ignore) (Algorithm.neighbors(fst s1,graph))
               
               if (snd s2) = 2
                    then 
                        let g3 = Algorithm.createGraph(graph.Vertices, graph.Edges)
                        g3.RemoveVertex(fst s1) |> ignore
                        Algorithm.ms1(g3, Seq.filter ((<>)(fst s1)) vertexset) |> Seq.append [(fst s1)]
                    else
                        if graph.ContainsEdge(fst s1,fst s2) && graph.ContainsEdge(fst s2,fst s3) && graph.ContainsEdge(fst s1,fst s3)
                            then Seq.empty
                            else
                                if graph.ContainsEdge(fst s1,fst s2) && graph.ContainsEdge(fst s1,fst s3)
                                    then edges2(s2,s3)
                                    else
                                        if graph.ContainsEdge(fst s2,fst s1) && graph.ContainsEdge(fst s2,fst s3)
                                            then edges2(s1,s3)
                                            else
                                                 if graph.ContainsEdge(fst s3,fst s1) && graph.ContainsEdge(fst s3,fst s2)
                                                    then edges2(s1,s2)
                                                    else 
                                                        if graph.ContainsEdge(fst s3,fst s1)
                                                            then edge1(fst s3,fst s1, s2)   
                                                            else
                                                                if graph.ContainsEdge(fst s2,fst s1)
                                                                    then edge1(fst s2,fst s1, s3)    
                                                                    else
                                                                        if graph.ContainsEdge(fst s2,fst s3)
                                                                            then edge1(fst s2,fst s3, s1)    
                                                                            else 
                                                                                let res1 = vertexN(fst s1,fst s2)
                                                                                match res1 with
                                                                                | Some x1 -> returnIS(x1, vertexset)
                                                                                | None ->   let res2 = vertexN(fst s2,fst s3)
                                                                                            match res2 with
                                                                                            | Some x2 -> returnIS(x2, vertexset)
                                                                                            | None ->   let res3 = vertexN(fst s1,fst s3)
                                                                                                        match res3 with
                                                                                                        | Some x3 -> returnIS(x3, vertexset)
                                                                                                        | None ->   if graph.AdjacentDegree(fst s1) = 1
                                                                                                                        then 
                                                                                                                            Algorithm.ms1(g1,Seq.filter ((<>)(fst s1)) vertexset) |> Seq.append [(fst s1)]
                                                                                                                        else
                                                                                                                            let max1 = Algorithm.ms1(g1,Seq.filter ((<>)(fst s1)) vertexset) |> Seq.append [(fst s1)]
                                                                                                                            let gr1 = Algorithm.createGraph(graph.Vertices, graph.Edges)
                                                                                                                            gr1.RemoveVertex(fst s1) |> ignore
                                                                                                                            gr1.RemoveVertex(fst s2) |> ignore
                                                                                                                            gr1.RemoveVertex(fst s3) |> ignore
                                                                                                                            Seq.iter (fun v -> gr1.RemoveVertex(v) |> ignore) (Algorithm.neighbors(fst s3,graph))
                                                                                                                            Seq.iter (fun v -> gr1.RemoveVertex(v) |> ignore) (Algorithm.neighbors(fst s2,graph))
                                                                                                                            let max2 = Algorithm.ms1(gr1, Algorithm.neighbors(fst s1,graph))
                                                                                                                            if (Seq.length max1) + 1 > (Seq.length max2) + 2
                                                                                                                                then max1 |> Seq.append [(fst s1)]
                                                                                                                                else max2 |> Seq.append [(fst s2);(fst s3)]
        | _ -> let s1 = Seq.head pair_sorted
               
               let ge1 = Algorithm.createGraph(graph.Vertices, graph.Edges)
               ge1.RemoveVertex(fst s1) |> ignore
               Seq.iter (fun v -> ge1.RemoveVertex(v) |> ignore) (Algorithm.neighbors(fst s1,graph))
               let max1 = Algorithm.ms(ge1)

               let ge2 = Algorithm.createGraph(graph.Vertices, graph.Edges)
               ge2.RemoveVertex(fst s1) |> ignore
               let max2 = Algorithm.ms2(ge2,Seq.filter ((<>)(fst s1)) vertexset)

               if (Seq.length max1) + 1 > (Seq.length max2)
                  then max1 |> Seq.append [(fst s1)]
                  else max2 

    static member ms1(graph: UndirectedGraph<int, Edge<int>>, vertexset: seq<int>):seq<int> =
        let pair_sorted = Algorithm.sortpairs(graph,vertexset)
        let take2 = Seq.take 2 pair_sorted
        let s1 = Seq.head take2
        let s2 = Seq.last take2

        let neighborsS1 = Algorithm.neighbors(fst s1,graph)
        let neighborsS2 = Algorithm.neighbors(fst s2,graph)

        let Ns1_Ns2 = Seq.fold (fun acc v -> if Seq.exists ((=)v) neighborsS1 then true else acc ) false neighborsS1

        let g1 = Algorithm.createGraph(graph.Vertices, graph.Edges)
        g1.RemoveVertex(fst s1) |> ignore
        Seq.iter (fun v -> g1.RemoveVertex(v)|>ignore) neighborsS1
        
        let g2 = Algorithm.createGraph(graph.Vertices, graph.Edges)
        g2.RemoveVertex(fst s2) |> ignore
        Seq.iter (fun v -> g2.RemoveVertex(v)|>ignore) neighborsS2

        let g3 = Algorithm.createGraph(graph.Vertices, graph.Edges)
        g3.RemoveVertex(fst s1) |> ignore
        g3.RemoveVertex(fst s2) |> ignore
        Seq.iter (fun v -> g3.RemoveVertex(v)|>ignore) neighborsS1
        Seq.iter (fun v -> g3.RemoveVertex(v)|>ignore) neighborsS2

        if snd(s1) <= 1 
            then Algorithm.ms(graph)
            else if graph.ContainsEdge(fst s1,fst s2)
                    then if (snd s1) < 3
                            then Algorithm.ms(graph)
                            else 
                                let max1 = Algorithm.ms(g1)
                                let max2 = Algorithm.ms(g2)
                                if (Seq.length max1) > (Seq.length max2)
                                    then max1 |> Seq.append [(fst s1)]
                                    else max2 |> Seq.append [(fst s2)]
                    else if Ns1_Ns2
                            then Algorithm.ms1(g3, vertexset)
                            else
                                if snd(s2) = 2
                                    then
                                        let E = Seq.head neighborsS1
                                        let F = Seq.last neighborsS1
                                        if graph.ContainsEdge(E,F)
                                            then Algorithm.ms(g1) |> Seq.append [(fst s1)]
                                            else
                                                let N_EF = Seq.fold ( fun acc x -> if Seq.exists ((=)x) acc then acc else acc |> Seq.append [x]) (Algorithm.neighbors(E,graph)) (Algorithm.neighbors(E,graph)) |>
                                                           Seq.filter ((<>) (fst s1))
                                                let more = Seq.fold (fun acc x -> (Seq.exists ((=)x) N_EF) && acc) true neighborsS2

                                                if ((Seq.length N_EF) > (Seq.length neighborsS2)) && more
                                                    then Algorithm.ms(g3) |> Seq.append [E;F;(fst s2)]
                                                    else
                                                        let g4 = Algorithm.createGraph(graph.Vertices, graph.Edges)
                                                        g4.RemoveVertex(fst s2) |> ignore
                                                        g4.RemoveVertex(E) |> ignore
                                                        g4.RemoveVertex(E) |> ignore
                                                        Seq.iter (fun v -> g4.RemoveVertex(v)|>ignore) (Algorithm.neighbors(E,graph))
                                                        Seq.iter (fun v -> g4.RemoveVertex(v)|>ignore) (Algorithm.neighbors(F,graph))
                                                        Seq.iter (fun v -> g4.RemoveVertex(v)|>ignore) (Algorithm.neighbors((fst s2),graph))
                                
                                                        let max1 = Algorithm.ms(g1)
                                                        let max2 = Algorithm.ms(g4)
                                
                                                        if (Seq.length max1) + 1 > (Seq.length max2) + 3
                                                            then max1 |> Seq.append [(fst s1)]
                                                            else max2 |> Seq.append [E;F;(fst s2)]       
                                    else
                                        let max1 = Algorithm.ms(g2)
                                        g1.RemoveVertex((fst s2)) |> ignore
                                        let max2 = Algorithm.ms2(g1, neighborsS2)
                                        if (Seq.length max1) > (Seq.length max2)
                                            then max1 |> Seq.append [(fst s2)]
                                            else max2 |> Seq.append [(fst s1)] 

        


    static member ms(graph: UndirectedGraph<int, Edge<int>>):seq<int> =
        if graph.VertexCount <= 1 
            then graph.Vertices
            else 
                let degrees = Seq.map (fun v -> graph.AdjacentDegree(v) ) graph.Vertices
                let minDegree = Seq.min degrees
                let A = Seq.find (fun v -> graph.AdjacentDegree(v) = minDegree) graph.Vertices
                let neighborsA = Algorithm.neighbors(A,graph)
                let maxDegree = Seq.map (fun v -> graph.AdjacentDegree(v) ) neighborsA |> Seq.max
                let B = Seq.find (fun v -> graph.AdjacentDegree(v) = maxDegree) neighborsA
                    
                let g1 = Algorithm.createGraph(graph.Vertices, graph.Edges)
                g1.RemoveVertex(A) |> ignore
                Seq.iter (fun v -> g1.RemoveVertex(v)|>ignore) neighborsA

                let gB = Algorithm.createGraph(graph.Vertices, graph.Edges)
                gB.RemoveVertex(B) |> ignore

                match graph.AdjacentDegree(A) with
                | 1 -> Algorithm.ms(g1) |> Seq.append [A]
                | 2 -> let B' = Seq.filter ((<>)B) neighborsA |> Seq.head
                       if graph.ContainsEdge(B,B')
                           then Algorithm.ms(g1) |> Seq.append [A]
                           else let g2 = Algorithm.createGraph(graph.Vertices, graph.Edges)
                                let N2_A = Seq.fold (fun acc x -> Seq.append (Algorithm.neighbors(x,graph)) acc) Seq.empty <| Algorithm.neighbors(A, graph) |>
                                           Seq.filter ((<>)A)
                                    
                                g2.RemoveVertex(B) |> ignore
                                g2.RemoveVertex(B') |> ignore
                                Algorithm.neighbors(B, graph) |> Seq.iter (fun v -> g2.RemoveVertex(v)|>ignore) 
                                Algorithm.neighbors(B', graph) |> Seq.iter (fun v -> g2.RemoveVertex(v)|>ignore)
                                   
                                let ms_res = Algorithm.ms(g2)
                                let ms2_res = Algorithm.ms2(g1,N2_A)

                                if (Seq.length ms_res) + 2 > (Seq.length ms2_res) + 1
                                    then
                                        ms_res |> Seq.append [B;B']
                                    else
                                        ms2_res |> Seq.append [A]
                | 3 -> let g2 = Algorithm.createGraph(graph.Vertices, graph.Edges)
                       g2.RemoveVertex(A) |> ignore
                       let ms2_res = Algorithm.ms2(g2, neighborsA)
                       let ms_res = Algorithm.ms(g1)
                       if (Seq.length ms_res) + 1 > (Seq.length ms2_res)
                           then
                               ms_res |> Seq.append [A]
                           else
                               ms2_res
                | _ -> if Algorithm.dominates(A,B,graph) 
                           then Algorithm.ms(gB)
                           else                   
                               let gb_res1 = Algorithm.ms(gB)
                               Algorithm.neighbors(B, graph) |> Seq.iter (fun v -> gB.RemoveVertex(v)|>ignore)
                               let gb_res2 = Algorithm.ms(gB)
                               if (Seq.length gb_res1) > (Seq.length gb_res2) + 1
                                   then gb_res1
                                   else gb_res2 |> Seq.append [B]


    static member Robson(vertices: int list, edges:Edge<int> list) =
        let graph = Algorithm.createGraph(vertices, edges)
        Algorithm.ms(graph)