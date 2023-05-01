import { Component } from '@angular/core';
import { MatAccordion } from '@angular/material/expansion';
import { ConfigBuilder } from '../classes/ConfigBuilder';
import { BioEvoService } from '../services/bio-evo.service';

@Component({
  selector: 'app-bio-evo-main',
  templateUrl: './bio-evo-main.component.html',
  styleUrls: ['./bio-evo-main.component.css']
})
export class BioEvoMainComponent {
  config_builder: ConfigBuilder = new ConfigBuilder()
  configs: string[] = []
  current_config: string = "No config"

  warning_universe: string = ""
  warning_environment: string = ""
  warning_individual: string = ""
  
  current_universe: string = ""
  universes: string[] = []
  new_universe: string = "My universe"
  
  new_environment: string = ""  
  env_by_univ: Map<string, string> = new Map<string,string>()
  
  new_individual: string = ""
  indiv_by_univ: Map<string, string[]> = new Map<string, string[]>() 

  public constructor(private bio_evo_service: BioEvoService) { }

  ngOnInit(): void {
    this.bio_evo_service.get_configs().subscribe(configs_names => {
      var cfg_arr = JSON.parse(configs_names)
      cfg_arr.forEach((cfg_name:string) => { 
        this.configs.push(cfg_name.replace('../config/', '').replace('.conf.json', ''))
      })
    })
  }

  select_config(cfg_name: string): void {
    this.current_config = cfg_name

    this.bio_evo_service.apply_config(cfg_name).subscribe(res => {
      debugger
      this.get_info()
    })
  }

  get_info(): void {
    this.bio_evo_service.get_info().subscribe(res => {
      debugger
    })
  }

  add_universe(): void {
    var isin = false
    this.universes.forEach( (universe: string) => {
      if(universe === this.new_universe) {
        isin = true
      }
    })

    if(isin) {
      this.warning_universe = this.new_universe + " already exists !"
    } else if (this.new_universe === "") {
      this.warning_universe = "Please give a name to the universe"
    } else {
      this.warning_universe = ""

      this.universes.push(this.new_universe)
      this.current_universe = this.new_universe

      this.env_by_univ.set(this.new_universe, "")
      this.indiv_by_univ.set(this.new_universe, [])
    }
  }

  add_environment(): void {
    debugger

    if(this.new_environment === "") {
      this.warning_environment = "Please give a name to the new environment"
    } else {
      this.warning_environment = ""

      this.env_by_univ.set(this.current_universe, this.new_environment)
    } 
  }

  add_individual(): void { 
    var individuals = this.indiv_by_univ.get(this.current_universe)
    if(individuals != undefined) {
      var isin = false
      individuals.forEach((individual: string) => {
        if(individual === this.new_individual) {
          isin = true
        }
      })

      if(isin) {
        this.warning_individual = this.new_individual + " already exists"
      } else if (this.new_individual === "") {
        this.warning_individual = "Please give a name to the individual"
      } else {
        this.warning_individual = ""

        individuals.push(this.new_individual)
        this.indiv_by_univ.set(this.current_universe, individuals)
      }
    }
  }
 
}
