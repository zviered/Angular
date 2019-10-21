import { Injectable } from '@angular/core';
import {HttpClient} from '@angular/common/http';

@Injectable({
  providedIn: 'root'
})

export class SysconfigService {

  sysConfig : any;
  
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
  public async ReadConfiguration () 
  {
      /*await this.http.get ('http://localhost:80/api/Target.xml',{ responseType: 'text' }).subscribe(
      (val) => {
          console.log("GET call successful value returned in body", val);
                      
          const parser = new DOMParser();
          const srcDOM = parser.parseFromString(val, "application/xml");
          this.sysConfig = this.xml2json (srcDOM);
      },
      response => {
          console.log("GET call in error", response);
      },
      () => {
          console.log("The GET observable is now completed.");
      }); */

    this.sysConfig = await this.http.get('http://localhost:80/api/Target.xml',{ responseType: 'text' }).toPromise();
    /*.then((data: any) => {
     
      console.time('request-length');
      console.log(data);
      console.timeEnd('request-length');

    });*/
    console.log(this.sysConfig);
  }

  /*************************************************************************************/
  constructor(private http: HttpClient) {
   console.log ('constructor SysconfigService');
   console.log (this.sysConfig);
  }
}
