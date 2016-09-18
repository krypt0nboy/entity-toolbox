<?php

/**
 * Class ThemeModel
 */
class ThemeModel extends ThemeRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'structure' => array(
          'variables'                     => array(
            'type'     => 'array',
            'method'   => 'buildVariables',
            'unset if' => 'is_empty:c:'
          ),
          'render element'                => array(
            'type'     => 'string',
            'method'   => 'buildRenderElement',
            'unset if' => 'is_empty:c:'
          ),
          'file'                          => array(
            'type'     => 'string',
            'method'   => 'buildFile',
            'unset if' => 'is_empty:c:'
          ),
          'path'                          => array(
            'type'     => 'string',
            'method'   => 'buildPath',
            'unset if' => 'is_empty:c:'
          ),
          'template'                      => array(
            'type'     => 'string',
            'method'   => 'builtTemplate',
            'unset if' => 'is_empty:c:'
          ),
          'function'                      => array(
            'type'     => 'string',
            'method'   => 'buildFunction',
            'unset if' => 'is_empty:c:'
          ),
          'base hook'                     => array(
            'type'     => 'string',
            'method'   => 'buildBaseHook',
            'unset if' => 'is_empty:c:'
          ),
          'pattern'                       => array(
            'type'     => 'string',
            'method'   => 'buildPattern',
            'unset if' => 'is_empty:c:'
          ),
          'preprocess functions'          => array(
            'type'     => 'array',
            'method'   => 'buildPreprocessFunctions',
            'unset if' => 'is_empty:c:'
          ),
          'override preprocess functions' => array(
            'type'     => 'array',
            'method'   => 'buildOverridePreprocessFunctions',
            'unset if' => 'is_empty:c:'
          ),
          'type'                          => array(
            'type'     => 'string',
            'method'   => 'buildType',
            'unset if' => 'is_empty:c:'
          ),
          'theme path'                    => array(
            'type'     => 'string',
            'method'   => 'buildThemePath',
            'unset if' => 'is_empty:c:'
          ),
        ),
      ),
      $args
    );
    parent::__construct($args);
  }
}