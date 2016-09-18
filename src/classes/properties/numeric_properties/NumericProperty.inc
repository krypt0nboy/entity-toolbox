<?php

/**
 * Class NumericPropertyBase
 */
class NumericProperty extends EntityToolboxPropertyBase {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'                => 'numeric',
        'default_php_type'            => 'numeric',
        'default_drupal_type'         => 'numeric',
        'default_reference'           => NULL,
        'default_multiple'            => FALSE,
        'default_schemas_fields_name' => array(
          'relation'          => NULL,
          'relation_revision' => NULL,
        ),
        'default_schemas_fields'      => array(
          'base'              => array(
            'type'     => 'int',
            'not null' => TRUE,
            'default'  => 0,
          ),
          'revision'          => array(
            'type'     => 'int',
            'not null' => TRUE,
            'default'  => 0,
          ),
          'relation'          => array(
            'type'     => 'int',
            'not null' => TRUE,
            'default'  => 0,
          ),
          'relation_revision' => array(
            'type'     => 'int',
            'not null' => TRUE,
            'default'  => 0,
          ),
        ),
        'default_forms'               => array(
          'edit' => array(
            'widget'   => 'textfield',
            'required' => FALSE,
          ),
        ),
        'default_value'               => array(
          'default' => 0,
        ),
        'default_callbacks'           => array(
          'getter'       => NULL,
          'setter'       => NULL,
          'validation'   => NULL,
          'permission'   => NULL,
          'default'      => NULL,
          'options_list' => NULL,
        ),
      ),
      $args
    );

    parent::__construct($args);
  }
}