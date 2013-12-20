<?php

/**
 * @file
 */
class component_entity_handler_component_entity_operations_field extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['wcid'] = 'wcid';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {

    $links = menu_contextual_links('component_entity', 'admin/content/component_entities/component_entity', array($this->get_value($values, 'wcid')));
    
    if (!empty($links)) {
      return theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline', 'operations'))));
    }
  }
}
