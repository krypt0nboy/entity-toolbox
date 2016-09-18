<?php

/**
 * Class DateProperty
 */
class DateProperty extends TimeProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'           => 'date',
        'default_schemas_fields' => array(
          'base'     => array(
            'type'     => 'int',
            'not null' => FALSE,
            'default'  => 0,
          ),
          'revision' => array(
            'type'     => 'int',
            'not null' => FALSE,
            'default'  => 0,
          ),
        ),
        'default_forms'          => array(
          'edit' => array(
            'expose'   => TRUE,
            'widget'   => 'textfield',
            'required' => FALSE,
          ),
        ),
      ),
      $args
    );
    parent::__construct($args);
  }
}