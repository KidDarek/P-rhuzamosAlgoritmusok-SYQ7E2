using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;

namespace Textsearch
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string[] text = File.ReadAllLines("text.txt");
            Console.WriteLine("What letter should i check for? ");
            char c = Console.ReadLine()[0];
            int counter = 0;
            int multiplier = 100000;
            Stopwatch sw = new Stopwatch();
            sw.Start();
            for (int k = 0; k < multiplier; k++)
            {
                counter = 0;
                for (int i = 0; i < text.Length; i++)
                {
                    for (int j = 0; j < text[i].Length; j++)
                    {
                        if (text[i][j] == c)
                        {
                            counter++;
                        }
                    }
                }
            }
            sw.Stop();
            Console.WriteLine("Counter: {0}", counter);
            Console.WriteLine("Runtime: {0} s", (double)sw.ElapsedMilliseconds / 1000.0);

            Stopwatch sw2 = new Stopwatch();
            sw2.Start();
            Parallel.For(0, text.Length, (index) =>
            {
                counter = 0;
                for (int i = 0; i < multiplier; i++)
                {
                    for (int j = 0; j < text[index].Length; j++)
                    {
                        if (text[index][j] == c)
                        {
                            counter++;
                        }
                    }
                }
            });
            sw2.Stop();
            Console.WriteLine("Counter: {0}", counter);
            Console.WriteLine("Runtime: {0} s", (double)sw2.ElapsedMilliseconds / 1000.0);

        }
    }
}
