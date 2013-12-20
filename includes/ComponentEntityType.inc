<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * The class used for component_entity type entities
 */
class ComponentEntityType extends Entity {
  
  public $type;
  public $label;
  
  public function __construct($values = array()) {
    parent::__construct($values, 'component_entity_type');
  }
  
}
