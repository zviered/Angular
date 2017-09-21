﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;

namespace HttpLstener
{
    class Program
    {
        public static string GetRequestPostData(HttpListenerRequest request)
        {
            if (!request.HasEntityBody)
            {
                return null;
            }
            using (System.IO.Stream body = request.InputStream) // here we have data
            {
                using (System.IO.StreamReader reader = new System.IO.StreamReader(body, request.ContentEncoding))
                {
                    return reader.ReadToEnd();
                }
            }
        }

        static void Main(string[] args)
        {
            var web = new HttpListener();

            web.Prefixes.Add("http://localhost:80/");

            Console.WriteLine("Listening..");

            web.Start();

            while (true)
            {
                HttpListenerContext context = web.GetContext();

                HttpListenerResponse response = context.Response;
                HttpListenerRequest request = context.Request;

                string s = GetRequestPostData(request);
                Console.WriteLine(s);

                var output = response.OutputStream;
                string responseString = "HTTP/1.0 200 OK\n\n";
                var buffer = System.Text.Encoding.UTF8.GetBytes(responseString);
                response.ContentLength64 = buffer.Length;
                response.Headers.Add("Access-Control-Allow-Origin", "*");

                output.Write(buffer, 0, buffer.Length);
            }

            /*if (request.HttpMethod == "POST" )
            {
                // Here i can read all parameters in string but how to parse each one i don't know  
                if (request.ContentType == "multipart/form-data")
                {
                    Console.WriteLine(request.ContentType);
                    int rc = response.Headers.Count;
                }
            }*/
        }
    }
}