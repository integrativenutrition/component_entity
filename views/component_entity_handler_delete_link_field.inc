<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying deletes links
 * as fields
 */


class component_entity_handler_delete_link_field extends component_entity_handler_link_field {
  function construct() {
    parent::construct();
    $this->additional_fields['type'] = 'type';
  }


  function render($values) {
    $type = $values->{$this->aliases['type']};
    
    //Creating a dummy component_entity to check access against
    $dummy_component_entity = (object) array('type' => $type);
    if (!component_entity_access('edit', $dummy_component_entity)) {
      return;
    }
    
    $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
    $wcid = $values->{$this->aliases['wcid']};
    
    return l($text, 'admin/content/component_entities/component_entity/' . $wcid . '/delete');
  }
}
