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
            string FileName=null, FilePath=null;

            web.Prefixes.Add("http://*:8000/");

            Console.WriteLine("Listening..");

            web.Start();

            while (true)
            {
                HttpListenerContext context = web.GetContext();

                HttpListenerResponse response = context.Response;
                HttpListenerRequest request = context.Request;

                response.StatusCode = 200;
                response.Headers.Add("Access-Control-Allow-Origin", "*");

                if (request.RawUrl == "/" &&
                    request.RawUrl.Length == 1)
                    FileName = "/index.html";
                else
                    FileName = request.RawUrl;

                Console.WriteLine(FileName);
                string Ext = Path.GetExtension(FileName);
                if (Ext == ".html")
                    response.ContentType = "text/html";
                else if (Ext == ".css")
                    response.ContentType = "text/css";
                else if (Ext == ".js")
                    response.ContentType = "application/javascript";
                else if (Ext == ".png")
                    response.ContentType = "image/png";
                else if (Ext == ".ttf")
                    response.ContentType = "application/font-sfnt";
                else if (Ext == ".ico")
                    response.ContentType = "image/vnd.microsoft.icon";

                FilePath = "d:/zvi_vered/git/ELTA_34/dist/Elta" + FileName;
                byte[] buffer = File.ReadAllBytes(FilePath);
                if (buffer.Length == 0)
                {
                    Console.WriteLine("Failed to find: "+FileName);
                    break;
                }
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
