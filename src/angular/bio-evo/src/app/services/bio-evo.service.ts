import { HttpClient, HttpParams } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class BioEvoService {
  apiUrl: string = "http://localhost:4300/bio-evo-api/"
  apiInfo: string = "info"
  
  constructor(private http: HttpClient) { }

  get_info(): Observable<any> {
    return this.http.get(this.apiUrl + this.apiInfo, {responseType: 'text'})
  }
  
  test(): Observable<any> {
    let queryParams = new HttpParams();
    queryParams = queryParams.append("page",1);

    debugger
    return this.http.get(this.apiUrl + "time", {responseType: 'text', params:queryParams})
  }
}

