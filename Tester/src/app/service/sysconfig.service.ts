import { Injectable } from '@angular/core';
import {HttpClient} from '@angular/common/http';

@Injectable({
  providedIn: 'root'
})

export class SysconfigService {

  /*************************************************************************************/
  private xml2json(srcDOM) {

    const children = [...srcDOM.children];
    if (!children.length) return srcDOM.innerHTML
  
    const jsonResult = Object.create(null),
      childIsArray = (x, y) => x.filter(z => z.nodeName === y.nodeName).length > 1;
  
    for (const child of children) {
      if (!childIsArray(children, child)) jsonResult[child.nodeName] = this.xml2json(child);
      else {
        if (jsonResult[child.nodeName] !== undefined) jsonResult[child.nodeName].push(this.xml2json(child));
        else jsonResult[child.nodeName] = [this.xml2json(child)];
      }
    }
  
    return jsonResult;
  }

  /*************************************************************************************/
  private ReadConfiguration () : any
  {
    this.http.get ('http://localhost:80/api/Target.xml',{ responseType: 'text' }).subscribe(
      (val) => {
          console.log("GET call successful value returned in body", val);
                      
          const parser = new DOMParser();
          const srcDOM = parser.parseFromString(val, "application/xml");
          console.log(this.xml2json (srcDOM));
          
      },
      response => {
          console.log("GET call in error", response);
      },
      () => {
          console.log("The GET observable is now completed.");
      }); 
      
      console.log ('Here');

  }

  /*************************************************************************************/
  constructor(private http: HttpClient) {
  
    var xml,res, text;
  
    console.log ('constructor SysconfigService');
    text = this.ReadConfiguration ();
    //console.log (text);
  }
}
