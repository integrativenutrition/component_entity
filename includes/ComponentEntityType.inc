<?php

/**
 * @file
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
