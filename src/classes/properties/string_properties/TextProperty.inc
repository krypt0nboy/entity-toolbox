<?php

/**
 * Class TextProperty
 */
class TextProperty extends StringProperty {

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'           => 'text',
        'default_serialize'      => TRUE,
        'default_schemas_fields' => array(
          'base'     => array(
            'type'   => 'text',
            'length' => NULL,
            'size'   => 'medium',
          ),
          'revision' => array(
            'type'   => 'text',
            'length' => NULL,
            'size'   => 'medium',
          ),
        ),
        'default_forms'          => array(
          'edit'   => array(
            'expose' => TRUE,
            'widget' => 'textarea',
            'cols'   => 5,
            'rows'   => 5,
          ),
          'inline' => array(
            'expose' => TRUE,
            'widget' => 'textarea',
            'cols'   => 5,
            'rows'   => 5,
          ),
        ),
      ),
      $args
    );
    parent::__construct($args);
  }
}