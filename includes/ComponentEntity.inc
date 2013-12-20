<?php

/**
 * @file
 */

/**
 * The class used for component_entity entities
 */
class ComponentEntity extends Entity {

  public function __construct($values = array()) {
    parent::__construct($values, 'component_entity');
  }

  protected function defaultLabel() {
    return $this->name;
  }

  protected function defaultUri() {
    return array('path' => 'component_entity/' . $this->wcid);
  }
  
  
}
