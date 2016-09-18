<?php

/**
 * Class UserProperty
 */
class UserProperty extends EntityProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'                => 'user',
        'default_php_type'            => 'object',
        'default_drupal_type'         => 'user',
        'default_reference'           => 'user',
        'default_has_revisions'       => TRUE,
        'default_has_translations'    => FALSE,
        'default_key'                 => 'uid',
        'default_schemas_fields_name' => array(
          'base'              => 'uid',
          'revision'          => 'uid',
          'relation'          => 'uid',
          'relation_revision' => 'uid',
        ),
        'default_schemas_fields'      => array(
          'base'     => array(
            'description' => 'The {users}.uid.',
          ),
          'relation' => array(
            'description' => 'The {users}.uid.',
          ),
        ),
        'default_views_expose'        => TRUE,
        'default_value'               => array(),
      ),
      $args
    );

    parent::__construct($args);
  }
}