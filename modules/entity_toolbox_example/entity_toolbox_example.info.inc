<?php

/**
 * Implements hook_entity_group_info().
 */
function entity_toolbox_example_entity_group_info() {
  $info            = array();
  $info['example'] = array(
    'label'       => t('Example'),
    'description' => t('Example entities.'),
    'path'        => 'admin/example',
    'classes'     => array(
      'group'      => 'ExampleGroup',
      'controller' => 'ExampleGroupController'
    ),
  );

  return $info;
}