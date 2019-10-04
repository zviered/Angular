using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.IO;

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
            //string msg = "{\"id\":0,\"size\":0}";
            string msg = "{\"id\":0,0}";

            web.Prefixes.Add("http://localhost:8000/");

            Console.WriteLine("Listening..");

            web.Start();

            while (true)
            {
                HttpListenerContext context = web.GetContext();

                HttpListenerResponse response = context.Response;
                HttpListenerRequest request = context.Request;

                string s = GetRequestPostData(request);
                Console.WriteLine(s);


                response.StatusCode = 200;
                response.Headers.Add("Access-Control-Allow-Origin", "*");
                response.ContentType = "text/html";
                
                byte[] buffer = Encoding.UTF8.GetBytes(msg);

                response.ContentLength64 = buffer.Length;
                Stream st = response.OutputStream;
                st.Write(buffer, 0, buffer.Length);

                response.Close();
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
