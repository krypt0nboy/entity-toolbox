<?php

/**
 * Implements hook_entity_group_info().
 */
function entity_toolbox_test_entity_group_info() {
  $info         = array();
  $info['tree'] = array(
    'label'       => t('Tree'),
    'description' => t('Tree entities.'),
    'path'        => 'admin/tree',
    'classes'     => array(
      'group'      => 'Tree',
      'controller' => 'TreeController'
    )
  );

  return $info;
}

/**
 * Implements hook_entity_toolbox_info().
 */
function entity_toolbox_test_entity_toolbox_info() {
  $info             = array();
  $info['foo']      = array(
    'fieldable'  => TRUE,
    'properties' => array(
      'displays' => array(
        'type' => 'display'
      )
    ),
    'group'      => 'tree',
  );
  $info['foo_type'] = array(
    'fieldable' => FALSE,
    'group'     => 'tree',
  );

  return $info;
}