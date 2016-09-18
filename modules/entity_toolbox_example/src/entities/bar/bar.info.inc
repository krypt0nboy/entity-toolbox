<?php

/**
 * Implements hook_entity_toolbox_info().
 */
function bar_entity_toolbox_info() {
  $info             = array();
  $info['bar']      = array(
    'fieldable' => TRUE,
    'group'     => 'example',
  );
  $info['bar_type'] = array(
    'fieldable' => FALSE,
    'group'     => 'example',
  );

  return $info;
}