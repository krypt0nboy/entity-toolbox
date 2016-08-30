<?php

/**
 * Implements hook_entity_toolbox_info().
 */
function entity_toolbox_test_entity_toolbox_info() {
  $info                 = array();
  $info['example']      = array(
    'fieldable' => TRUE,
    'group'     => 'example',
  );
  $info['example_type'] = array(
    'fieldable' => FALSE,
    'group'     => 'example',
  );

  return $info;
}