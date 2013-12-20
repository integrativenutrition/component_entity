<?php

/**
 * @file
 */


class component_entity_handler_delete_link_field extends component_entity_handler_link_field {
  function construct() {
    parent::construct();
    $this->additional_fields['type'] = 'type';
  }


  function render($values) {
    $type = $values->{$this->aliases['type']};
    $dummy_component_entity = (object) array('type' => $type);
    if (!component_entity_access('edit', $dummy_component_entity)) {
      return;
    }
    $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
    $wcid = $values->{$this->aliases['wcid']};
    
    return l($text, 'admin/content/component_entities/component_entity/' . $wcid . '/delete');
  }
}
