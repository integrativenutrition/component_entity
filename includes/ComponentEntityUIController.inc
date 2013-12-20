<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * UI controller.
 */
class ComponentEntityUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults. Main reason for doing this is that
   * parent class hook_menu() is optimized for entity type administration.
   */
  public function hook_menu() {
    
    $items = array();
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%' . $this->entityType;

    $items[$this->path] = array(
      'title' => 'ComponentEntities',
      'description' => 'Add edit and update component_entities.',
      'page callback' => 'system_admin_menu_block_page',
      'access arguments' => array('access administration pages'),
      'file path' => drupal_get_path('module', 'system'),
      'file' => 'system.admin.inc',
      'type' => MENU_LOCAL_TASK,
    );
    
    // Change the add page menu to multiple types of entities
    $items[$this->path . '/add'] = array(
      'title' => 'Add a component_entity',
      'description' => 'Add a new component_entity',
      'page callback'  => 'component_entity_add_page',
      'access callback'  => 'component_entity_access',
      'access arguments' => array('edit'),
      'type' => MENU_NORMAL_ITEM,
      'weight' => 20,
      'file' => 'component_entity.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])

    );
    
    // Add menu items to add each different type of entity.
    foreach (component_entity_get_types() as $type) {
      $items[$this->path . '/add/' . $type->type] = array(
        'title' => 'Add ' . $type->label,
        'page callback' => 'component_entity_form_wrapper',
        'page arguments' => array(component_entity_create(array('type' => $type->type))),
        'access callback' => 'component_entity_access',
        'access arguments' => array('edit', 'edit ' . $type->type),
        'file' => 'component_entity.admin.inc',
        'file path' => drupal_get_path('module', $this->entityInfo['module'])
      );
    }

    // Loading and editing component_entity entities
    $items[$this->path . '/component_entity/' . $wildcard] = array(
      'page callback' => 'component_entity_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'component_entity_access',
      'access arguments' => array('edit', $id_count + 1),
      'weight' => 0,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'file' => 'component_entity.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    $items[$this->path . '/component_entity/' . $wildcard . '/edit'] = array(
      'title' => 'Edit',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    );
    
    $items[$this->path . '/component_entity/' . $wildcard . '/delete'] = array(
      'title' => 'Delete',
      'page callback' => 'component_entity_delete_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'component_entity_access',
      'access arguments' => array('edit', $id_count + 1),
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
      'weight' => 10,
      'file' => 'component_entity.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    
    // Menu item for viewing component_entities
    $items['component_entity/' . $wildcard] = array(
      //'title' => 'Title',
      'title callback' => 'component_entity_page_title',
      'title arguments' => array(1),
      'page callback' => 'component_entity_page_view',
      'page arguments' => array(1),
      'access callback' => 'component_entity_access',
      'access arguments' => array('view', 1),
      'type' => MENU_CALLBACK,
    );
    return $items;
  }
  
  
  /**
   * Create the markup for the add ComponentEntity Entities page within the class
   * so it can easily be extended/overriden.
   */ 
  public function addPage() {
    $item = menu_get_item();
    $content = system_admin_menu_block($item);

    if (count($content) == 1) {
      $item = array_shift($content);
      drupal_goto($item['href']);
    }    
        
    return theme('component_entity_add_list', array('content' => $content));
  }
  
}


