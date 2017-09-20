import {Injectable} from "@angular/core";
import {Http, URLSearchParams, Headers} from "@angular/http";

const BASE_URL = 'http://localhost:80';

@Injectable()
export class HTTP{
  private http: any;

  constructor(http: Http){
    this.http = http;
  }

  get(method: string, payload: any = {}):any{
    let params = new URLSearchParams();
    for(let key in payload){
      params.set(key, payload[key]);
    }
    return this.http.get(`${BASE_URL}/${method}`, {
      search: params
    }).map(res => res.json());
  }

  post(method: string, payload: any = {}):any{
    return this.http.post(`${BASE_URL}/${method}`, payload).map(res => res.json());
  }

  delete(method: string, payload: any = {}):any{
    return this.http.delete(`${BASE_URL}/${method}`, payload).map(res => res.json());
  }

  put(method: string, payload: any = {}):any{
    return this.http.put(`${BASE_URL}/${method}`, payload).map(res => res.json());
  }

  patch(method: string, payload: any = {}): any {
    return this.http.patch(`${BASE_URL}/${method}`, payload).map(res => res.json());
  }

  upload(method: string, payload: any = {}, file: any):any{
    let params = new FormData();
    params.append("file", file);
    for(let key in payload){
      params.append(key, payload[key]);
    }
    let headers = new Headers();

    headers.append('Content-Type', 'multipart/form-data');
    return this.http.post(`${BASE_URL}/${method}`, params, headers).map(res => res.json());
  }

}