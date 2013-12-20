<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * The Controller for ComponentEntity entities
 */
class ComponentEntityController extends EntityAPIController {
  public function __construct($entityType) {
    parent::__construct($entityType);
  }


  /**
   * Create a component_entity - we first set up the values that are specific
   * to our component_entity schema but then also go through the EntityAPIController
   * function.
   * 
   * @param $type
   *   The machine-readable type of the component_entity.
   *
   * @return
   *   A component_entity object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our ComponentEntity
    $values += array( 
      'wcid' => '',
      'is_new' => TRUE,
      'title' => '',
      'created' => '',
      'changed' => '',
      'data' => '',
    );
    
    $component_entity = parent::create($values);
    return $component_entity;
  }
  
  /**
   * Overriding the buldContent function to add entity specific fields
   */
  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $content = parent::buildContent($entity, $view_mode, $langcode, $content);
    return $content;
  }
  
}

