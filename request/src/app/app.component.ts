import { Component } from '@angular/core';
import {HttpClient} from '@angular/common/http';
import {Http} from '@angular/http';
import {IsAliveRequest} from '../icd/PcToTgtIcd';
import {IsAliveReply} from '../icd/PcToTgtIcd';
import {WriteWaveformRequest} from '../icd/PcToTgtIcd';
//import {HTTP} from '../services/http/http-service.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})

export class AppComponent {
  title = 'app works!';
  constructor(private http: HttpClient)
  {
    var request = IsAliveRequest;
    var response = IsAliveReply;
    
    var ReadInfoRequest = {
      "id":2,
      "device":0
  }
    console.log ('constructor');

    console.log (request);

    let body: any;
    body = ReadInfoRequest;
    this.http.post('http://localhost:80', 
    JSON.stringify({
      body: 'bar',
      title: 'foo',
      userId: 1
    })).subscribe (data => {console.log ('response',data);});
  }
}
