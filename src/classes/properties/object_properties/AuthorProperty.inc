<?php

/**
 * Class AuthorProperty
 */
class AuthorProperty extends UserProperty {

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'           => 'author',
        'default_drupal_type'    => 'user',
        'default_reference'      => 'user',
        'default_required'       => TRUE,
        'default_name'           => 'author',
        'default_label'          => 'Author',
        'default_description'    => 'The %toolbox_info_labels_single_lowercase% author.',
        'default_key'            => 'uid',
        'default_callbacks'      => array(
          'default' => 'user_id'
        ),
        'default_schemas_fields' => array(
          'base'     => array(
            'description' => 'The {users}.uid that created the %toolbox_info_labels_single%.',
          ),
          'revision' => array(
            'description' => 'The {users}.uid that created the %toolbox_info_labels_single%.',
          ),
        ),
        'default_views_expose'   => TRUE,
      ),
      $args
    );

    parent::__construct($args);
  }
}