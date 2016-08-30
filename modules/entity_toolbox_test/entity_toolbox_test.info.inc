<?php

/**
 * Implements hook_entity_toolbox_info().
 */
function entity_toolbox_test_entity_toolbox_info() {
  $info                 = array();
  $info['product']      = array(
    'fieldable'  => TRUE,
    'properties' => array(
      'display' => array(
        'type' => 'display'
      )
    ),
    'group'      => 'catalog',
  );
  $info['product_type'] = array(
    'fieldable' => FALSE,
    'group'     => 'catalog',
  );

  return $info;
}

/**
 * Implements hook_entity_group_info().
 */
function entity_toolbox_test_entity_group_info() {
  $info            = array();
  $info['catalog'] = array(
    'label'       => t('Catalog'),
    'description' => t('Catalog entities.'),
    'path'        => 'admin/hedios/catalog',
    'classes'     => array(
      'group'      => 'Catalog',
      'controller' => 'CatalogController'
    ),
    'entities'    => array()
  );

  return $info;
}