import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class DataService {

  public _fullName : string;

  constructor() { 
    console.log ('DataService');
  }
}
