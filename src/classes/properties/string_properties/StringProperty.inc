<?php

/**
 * Class StringProperty
 */
class StringProperty extends EntityToolboxPropertyBase {

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'                => 'string',
        'default_php_type'            => 'string',
        'default_drupal_type'         => 'text',
        'default_reference'           => NULL,
        'default_serialize'           => TRUE,
        'default_tables'              => array(
          'relation'          => NULL,
          'relation_revision' => NULL,
        ),
        'default_schemas_fields_name' => array(
          'base'              => '',
          'revision'          => '',
        ),
        'default_schemas_fields'      => array(
          'base'              => array(
            'type'     => 'varchar',
            'length'   => 255,
            'not null' => TRUE,
            'default'  => '',
          ),
          'revision'          => array(
            'type'     => 'varchar',
            'length'   => 255,
            'not null' => TRUE,
            'default'  => '',
          ),
          'relation'          => NULL,
          'relation_revision' => NULL,
        ),
        'default_forms'               => array(
          'edit'   => array(
            'expose'   => TRUE,
            'widget'   => 'textfield',
            'required' => FALSE,
            'cols'     => NULL,
            'rows'     => NULL,
          ),
          'clone'  => array(
            'expose' => FALSE,
          ),
          'inline' => array(
            'expose'   => TRUE,
            'widget'   => 'textfield',
            'required' => FALSE,
            'cols'     => NULL,
            'rows'     => NULL,
          ),
        ),
      ),
      $args
    );
    parent::__construct($args);
  }
}