<?php

/**
 * Implements hook_entity_toolbox_info().
 */
function foo_entity_toolbox_info() {
  $info             = array();
  $info['foo']      = array(
    'fieldable' => TRUE,
    'group'     => 'example',
  );
  $info['foo_type'] = array(
    'fieldable' => FALSE,
    'group'     => 'example',
  );

  return $info;
}