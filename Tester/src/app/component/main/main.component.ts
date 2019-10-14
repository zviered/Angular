import { Component, OnInit, Input} from '@angular/core';
import {HttpClient, HttpHeaders, HttpHeaderResponse} from '@angular/common/http';
import {WritePciRequest} from '../../../icd/WritePci'
import { ReadPciRequest } from 'src/icd/ReadPci';
import {DataService} from '../../data.service'

const BASE_URL = 'http://localhost:8000';

@Component({
  selector: 'app-main',
  templateUrl: './main.component.html',
  styleUrls: ['./main.component.scss']
})

export class MainComponent implements OnInit {

  writeBar: number;
  writeOffset: number;
  writeData: number;

  readBar: number;
  readOffset: number;
  readData: number;

  writePciRequest : WritePciRequest;
  readPciRequest : ReadPciRequest;
  
  /********************************************************************/
  constructor(private http: HttpClient, svc: DataService) 
  { 
    console.log ('constructor MainComponent');
    this.writePciRequest = new WritePciRequest;
    this.readPciRequest = new ReadPciRequest;
    svc._fullName = 'zvika vered';
    console.log (svc._fullName);
  }

  /********************************************************************/
  public onPciWrite()
  {
    this.writePciRequest.Bar = this.writeBar;
    this.writePciRequest.Data = this.writeData;
    this.writePciRequest.Offset = this.writeOffset;
 
    console.log (this.writePciRequest);

     var body = JSON.stringify(this.writePciRequest);
    this.http.post (`${BASE_URL}`,body).subscribe(
      (val) => {
          console.log("POST call successful value returned in body", 
                      val);
      },
      response => {
          console.log("POST call in error", response);
      },
      () => {
          console.log("The POST observable is now completed.");
      });        
  }
  
  /********************************************************************/
  public onPciRead()
  {
    this.readPciRequest.Bar = this.readBar;
    this.readPciRequest.Offset = this.readOffset;
 
    console.log (this.readPciRequest);

    var body = JSON.stringify(this.readPciRequest);
    this.http.post (`${BASE_URL}`,body).subscribe(
      (val) => {
          console.log("POST call successful value returned in body", 
                      val);
          this.readData = val[3];
      },
      response => {
          console.log("POST call in error", response);
      },
      () => {
          console.log("The POST observable is now completed.");
      });        
  }

  /********************************************************************/
  ngOnInit() {
  }

}
