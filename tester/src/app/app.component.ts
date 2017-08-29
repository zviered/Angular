import { Component } from '@angular/core';
import {
  Router
} from '@angular/router';
import {AppClass} from './app.class';
import {HttpClient} from '@angular/common/http';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})

export class AppComponent {

  app: AppClass;
  selectedOption: string;

  constructor(private http: HttpClient) {

    const file = './person.json';
    this.app = new AppClass(http);
  };

  fileChange(event) {
    let fileList: FileList = event.target.files;
    if(fileList.length > 0) {
      let file: File = fileList[0];
      this.upload ('post','',file);
    }
  }

  upload(method: string, payload: any = {}, file: any): any {
    let params = new FormData();
    params.append("file", file);
    for (let key in payload) {
      params.append(key, payload[key]);
    }
    let headers = new Headers();
    headers.append('Content-Type', 'multipart/form-data');
    return this.http.post(`${'/api'}/${method}`, params, headers);
  }
}
