<?php

/**
 * Implements hook_entity_toolbox_entity_info().
 */
function entity_toolbox_test_entity_toolbox_entity_info() {
  $info            = array();
  $info['product'] = array(
    'has_revisions'    => TRUE,
    'has_translations' => TRUE,
    'fieldable'        => TRUE,
    'module'           => 'hedios_catalog',
    'exportable'       => FALSE,
    'paths'            => array(
      'root'   => '',
      'admin'  => 'products',
      'manage' => 'edit'
    ),
    'properties'       => array(
      'product_id' => array('type' => 'id'),
      'type'       => array('type' => 'bundle'),
      'name'       => array(
        'type'             => 'tiny_text',
        'description'      => 'The product name.',
        'key'              => 'label',
        'has_revisions'    => TRUE,
        'has_translations' => FALSE,
      ),
      'author'     => array(
        'type'                => 'reference',
        'reference'           => 'user',
        'key'                 => 'uid',
        'description'         => 'The product author.',
        'has_revisions'       => TRUE,
        'has_translations'    => FALSE,
        'callbacks'           => array(
          'default' => 'user_id',
        ),
        'schemas_field_names' => array(
          'base'     => 'uid',
          'revision' => 'uid',
        )
      ),
      'created'    => array(
        'type'          => 'timestamp',
        'description'   => '',
        'has_revisions' => FALSE,
        'callbacks'     => array(
          'default' => 'request_time',
        ),
      ),
      'changed'    => array(
        'type'          => 'timestamp',
        'description'   => '',
        'has_revisions' => TRUE,
        'callbacks'     => array(
          'default' => 'request_time',
        ),
      )
    ),
    'group'            => 'catalog'
  );

  return $info;
}