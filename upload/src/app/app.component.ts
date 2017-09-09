import { Component } from '@angular/core';
import 'rxjs/add/operator/map';
import { Http} from '@angular/http';
import {HttpClient} from '@angular/common/http';
import {RequestOptions, Request, RequestMethod, Headers} from '@angular/http';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'app works!';
  constructor(private http: Http/*private http: HttpClient*/)
  {}

  addItem(List) {
    console.log (List);
    let fileList: FileList = List;
    let file: File = fileList[0];
    let body:FormData = new FormData();
    body.append('uploadFile', file, file.name);
    let headers = new Headers();
    /** No need to include Content-Type in Angular 4 */
    headers.append('Content-Type', 'multipart/form-data');
    headers.append('Accept', 'application/json');
    let options = new RequestOptions({ headers: headers });
    body.append('uploadFile', file, file.name);
    
    this.http.post(`${'http://192.168.14.66'}`, body, options).subscribe (data => {console.log ('response',data);});
  }
}
