<?php

/**
 * @file
 */

/**
 * Description of ComponentEntityTypeController
 *
 * @author HaiNN
 */

/**
 * The Controller for ComponentEntity entities
 */
class ComponentEntityTypeController extends EntityAPIControllerExportable {
  public function __construct($entityType) {
    parent::__construct($entityType);
  }
  
   /**
   * Create a component_entity type - we first set up the values that are specific
   * to our component_entity type schema but then also go through the EntityAPIController
   * function.
   * 
   * @param $type
   *   The machine-readable type of the component_entity.
   *
   * @return
   *   A component_entity type object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our ComponentEntity
    $values += array( 
      'id' => '',
      'is_new' => TRUE,
      'data' => '',
    );
    $component_entity_type = parent::create($values);
    return $component_entity_type;
  }
}

