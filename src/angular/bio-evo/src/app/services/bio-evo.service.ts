import { HttpClient, HttpParams } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { EnvironmentParamsLinear } from '../classes/Environments/EnvironmentLinear';
import { UtilsService } from './utils.service';
import { InstantiateExpr } from '@angular/compiler';

@Injectable({
  providedIn: 'root'
})
export class BioEvoService {
  apiUrl: string = "http://localhost:4301/bio-evo-api/"

  post: string = "instr"
  cfg: string = "get-configs"
  cfg_apply: string = "apply-config"
  info: string = "info"
  current_info: string = "current-info"
  info_type: string = "get-info-type"

  env_linear:string = "environment-linear"
  
  constructor(private http: HttpClient) { }

  get_configs(): Observable<any> {
    return this.http.get(this.apiUrl + this.cfg, {responseType: 'text'})
  }
  apply_config(cfg_name:string): Observable<any> {
    return this.http.post(this.apiUrl + this.cfg_apply, '../config/' + cfg_name + '.conf.json')
  } 

  get_current_info(): Observable<any> {
    return this.http.get(this.apiUrl + this.current_info, {responseType: 'text'})
  }

  get_info(): Observable<any> {
    return this.http.get(this.apiUrl + this.info, {responseType: 'text'})
  }

  get_info_type(entity_type: string): Observable<any> {
    let queryParams = new HttpParams();
    queryParams = queryParams.append("entity-type", entity_type);


    return this.http.get(this.apiUrl + this.info_type, {responseType: 'text', params:queryParams})
  }

  test(): Observable<any> {
    let queryParams = new HttpParams();
    queryParams = queryParams.append("page",1);

    debugger
    return this.http.get(this.apiUrl + "time", {responseType: 'text', params:queryParams})
  } 

  exec_instructions(json_instructions: string): Observable<any> {
    return this.http.post(this.apiUrl+this.post, json_instructions, {responseType: 'text'})
  }

  exec_instruction(instruction: Object): Observable<any> {
    var instructions: Object = {
      "nb instructions": 2,
      "instruction 1": instruction,
      "instruction 2": {
        name: "END"
      }
    }
    return this.exec_instructions(JSON.stringify(instructions));
  }
}

