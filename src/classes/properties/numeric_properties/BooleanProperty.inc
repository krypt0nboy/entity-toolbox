<?php

/**
 * Class BooleanProperty
 */
class BooleanProperty extends NumericProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'           => 'boolean',
        'default_php_type'       => 'boolean',
        'default_drupal_type'    => 'boolean',
        'default_schemas_fields' => array(
          'base'              => array(
            'size' => 'tiny',
          ),
          'revision'          => array(
            'size' => 'tiny',
          ),
          'relation'          => array(
            'size' => 'tiny',
          ),
          'relation_revision' => array(
            'size' => 'tiny',
          ),
        ),
        'default_forms'          => array(
          'edit' => array(
            'widget'   => 'checkbox',
            'required' => FALSE,
          ),
        ),
        'default_value'          => array(
          'default' => 0,
        ),
      ),
      $args
    );

    parent::__construct($args);
  }
}