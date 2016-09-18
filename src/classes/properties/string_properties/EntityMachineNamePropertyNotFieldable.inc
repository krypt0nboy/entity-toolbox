<?php

/**
 * Class EntityMachineNamePropertyNotFieldable
 */
class EntityMachineNamePropertyNotFieldable extends EntityMachineNameProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_description' => 'A unique machine-readable name for this %toolbox_info_labels_single_lowercase%. It must only contain lowercase letters, numbers, and underscores.',
        'default_name'        => 'type',
        'default_key'         => 'name',
        'default_callbacks'   => array(
          'options_list' => '%toolbox_info_entity_type%_get_types',
        ),
        'default_is_unique'   => TRUE,
      ),
      $args
    );
    parent::__construct($args);
  }
}
