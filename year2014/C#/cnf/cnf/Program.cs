using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace cnf
{
    public abstract class Variable
    {
        public String strName;
        public String Name{ 
            get { return strName;} 
            set { strName = value;}   
        }
    }

    class Epsilon : Variable
    {

    }


    class Term : Variable
    {
    
    }

    class NonTerm : Variable
    {

    }

    class Sentence
    {
        public Sentence(String str, Grammar g)
        {
            String[] vars = str.Split(' ');
            foreach (string s in vars)
            {
                //if (s.Trim() != "")
                    Console.WriteLine(s);
            }
            String leftName = vars[0];
            //NonTerm left = new NonTerm();
        }
        public NonTerm left;
        public List<Variable> right; 


    }

    class Grammar {
        public Grammar(String[] gr) 
        {
            sentences = new List<Sentence>();
            foreach (String str in gr)
            {
                Sentence S = new Sentence(str, this);
                sentences.Add(S);
            }
        }

        public NonTerm start;
        public List<Sentence> sentences;
    }

    class Program
    {
        static void Main(string[] args)
        {
            String[] file = System.IO.File.ReadAllLines("../../Test1.txt");
            Grammar G = new Grammar(file);

        }
    }
}
