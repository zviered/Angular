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

  fileChange(event) {
    let fileList: FileList = event.target.files;

    let file: File = fileList[0];
    let body: FormData = new FormData();
    let headers = new Headers();
    // No need to include Content-Type in Angular 4 
    headers.append('Content-Type', 'multipart/form-data');
    console.log ('name='+file.name+ ' size='+file.size);
    headers.append('Accept', 'application/json');
    let options = new RequestOptions({ headers: headers });
    body.append('uploadFile', file, file.name);

    this.http.post(`${'http://localhost:80'}`, body, options).subscribe (data => {console.log ('response',data);});
  }
}
