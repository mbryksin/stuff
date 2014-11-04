using System;
using System.Collections.Generic;
using NUnit.Framework.Constraints;
using Algorithms;
using QuickGraph;

namespace NUnit.Framework.UnitTests
{
    [TestFixture]
    public class UnitTest1
    {
        [Test]
        public void TestMethod1()
        {
            var edges = new SEdge<int>[] {};
            var vertices = new List<int>();
            var result = Algorithms.IndependentSet.Robson(vertices, edges);
            Assert.IsTrue(result == 0);
        }
    }
}
