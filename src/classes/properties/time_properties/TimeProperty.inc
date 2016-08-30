<?php

/**
 * Class TimeProperty
 */
class TimeProperty extends EntityToolboxPropertyBase {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'                   => 'time',
        'default_php_type'               => 'integer',
        'default_drupal_type'            => 'date',
        'default_has_translations'       => FALSE,
        'default_schemas_fields'         => array(
          'base'     => array(
            'type'        => 'int',
            'not null'    => FALSE,
          ),
          'revision' => array(
            'type'        => 'int',
            'not null'    => FALSE,
          ),
        ),
        'default_forms'                  => array(
          'edit'   => array(
            'expose'   => FALSE,
            'widget'   => 'textfield',
            'required' => FALSE,
          ),
          'inline' => array(
            'expose'   => FALSE,
            'required' => FALSE,
          ),
        ),
        'default_is_unique'              => FALSE,
        'default_views_expose'           => TRUE,
      ),
      $args
    );
    parent::__construct($args);
  }
}