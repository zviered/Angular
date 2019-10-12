import { Component, OnInit } from '@angular/core';
import {HttpClient, HttpHeaders, HttpHeaderResponse} from '@angular/common/http';
import {WritePciRequest} from '../../../icd/WritePci'
import { ReadPciRequest } from 'src/icd/ReadPci';

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
  constructor(private http: HttpClient) 
  { 
    this.writePciRequest = new WritePciRequest;
    this.readPciRequest = new ReadPciRequest;
  }

  /********************************************************************/
  public onPciWrite()
  {
    this.writePciRequest.Bar = this.writeBar;
    this.writePciRequest.Data = this.writeData;
    this.writePciRequest.Offset = this.writeOffset;
 
    //alert ('onClick');
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
  public processFile(theFile) 
  {
    return function(event) { 
      var content = event.target.result; 
      console.log (content); 
    }
  }

  /********************************************************************/
  public onOpenFile (event)
  {
    var xmlDoc;
    var parser;
    var text = "<bookstore><book>" +
                "<title>Everyday Italian</title>" +
                "<author>Giada De Laurentiis</author>" +
                "<year>2005</year>" +
                "</book></bookstore>";

    var textJson = '{ "employees" : [' +
    '{ "firstName":"John" , "lastName":"Doe" },' +
    '{ "firstName":"Anna" , "lastName":"Smith" },' +
    '{ "firstName":"Peter" , "lastName":"Jones" } ]}';

    parser = new DOMParser();
    xmlDoc = parser.parseFromString(text,"text/xml");
    console.log('xmldoc');
    console.log(xmlDoc);

    console.log('jsonDoc');
    var jsonDoc = JSON.parse(textJson);
    console.log (jsonDoc);

    var f = event.files[0];
    let fileReader = new FileReader();
    fileReader.onloadend = this.processFile(f);
    fileReader.readAsText(f);
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
