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

                //response.ContentLength64 = buffer.Length;
                Stream st = response.OutputStream;
                //buffer.Length is the body length
                st.Write(buffer, 0, buffer.Length);

                BinaryWriter writer = new BinaryWriter(File.Open(FileName, FileMode.Create));
                writer.Write(buffer, 0, buffer.Length);
                writer.Close();

                response.Close();
            }
        }
    }
}
