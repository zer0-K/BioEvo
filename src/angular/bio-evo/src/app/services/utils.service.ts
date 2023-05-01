import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class UtilsService {

  constructor() { }

  to_string(tab: number[]): string {
    var res = "["

    for(let i=0; i<tab.length; i++) {
      res += tab[i].toString() + ","
    }

    if(tab.length>0) {
      res.slice(0,-1)
    }

    res += "]"
    return res
  }
}
