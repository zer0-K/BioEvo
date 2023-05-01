import { HttpClient, HttpParams } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { EnvironmentLinear } from '../classes/Environments/EnvironmentLinear';
import { UtilsService } from './utils.service';

@Injectable({
  providedIn: 'root'
})
export class BioEvoService {
  apiUrl: string = "http://localhost:4300/bio-evo-api/"

  post: string = "instr"
  cfg: string = "get-configs"
  cfg_apply: string = "apply-config"
  info: string = "info"

  env_linear:string = "environment-linear"
  
  constructor(private http: HttpClient) { }

  get_configs(): Observable<any> {
    return this.http.get(this.apiUrl + this.cfg, {responseType: 'text'})
  }
  apply_config(cfg_name:string): Observable<any> {
    return this.http.post(this.apiUrl + this.cfg_apply, '../config/' + cfg_name + '.conf.json')
  } 

  get_info(): Observable<any> {
    return this.http.get(this.apiUrl + this.info, {responseType: 'text'})
  }
  
  test(): Observable<any> {
    let queryParams = new HttpParams();
    queryParams = queryParams.append("page",1);

    debugger
    return this.http.get(this.apiUrl + "time", {responseType: 'text', params:queryParams})
  } 

  exec_instr(json_instructions: string): Observable<any> {
    return this.http.post(this.apiUrl+this.post, json_instructions)
  }
}

